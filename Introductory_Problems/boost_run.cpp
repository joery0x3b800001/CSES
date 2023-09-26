#include <boost/gil.hpp>
#include <boost/gil/extension/dynamic_image/dynamic_image_all.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/jpeg/old.hpp>
#include <bits/stdc++.h>

typedef uint8_t bits8;

using namespace boost::gil;
using namespace std;

void x_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
{
 	for (int y=0; y<src.height(); ++y)
      	for (int x=1; x<src.width()-1; ++x)
           dst(x,y) = (src(x-1,y) - src(x+1,y)) / 2;
}

void ComputeXGradientGray8(const unsigned char* src_pixels, ptrdiff_t src_row_bytes, int w, int h,
                           signed char* dst_pixels, ptrdiff_t dst_row_bytes)
{
  gray8c_view_t src = interleaved_view(w, h, (const gray8_pixel_t*)src_pixels,src_row_bytes);
  gray8s_view_t dst = interleaved_view(w, h, (     gray8s_pixel_t*)dst_pixels,dst_row_bytes);
  x_gradient(src,dst);
}

// void x_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   for (int y=0; y<src.height(); ++y)
//   {
//       gray8c_view_t::x_iterator src_it = src.row_begin(y);
//       gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

//       for (int x=1; x<src.width()-1; ++x)
//           dst_it[x] = (src_it[x-1] - src_it[x+1]) / 2;
//   }
// }


// void y_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   for (int x=0; x<src.width(); ++x)
//   {
//       gray8c_view_t::y_iterator src_it = src.col_begin(x);
//       gray8s_view_t::y_iterator dst_it = dst.col_begin(x);

//       for (int y=1; y<src.height()-1; ++y)
//           dst_it[y] = (src_it[y-1] - src_it[y+1])/2;
//   }
// }

// void y_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   gray8c_view_t::xy_locator src_loc = src.xy_at(0,1);
//   for (int y=1; y<src.height()-1; ++y)
//   {
//       gray8s_view_t::x_iterator dst_it  = dst.row_begin(y);

//       for (int x=0; x<src.width(); ++x)
//   {
//           (*dst_it) = (src_loc(0,-1) - src_loc(0,1)) / 2;
//           ++dst_it;
//           ++src_loc.x(); // each dimension can be advanced separately
//       }
//       src_loc+=point2<std::ptrdiff_t>(-src.width(),1); // carriage return
//   }
// }

// void y_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   gray8c_view_t::xy_locator src_loc = src.xy_at(0,1);
//   gray8c_view_t::xy_locator::cached_location_t above = src_loc.cache_location(0,-1);
//   gray8c_view_t::xy_locator::cached_location_t below = src_loc.cache_location(0, 1);

//   for (int y=1; y<src.height()-1; ++y)
//   {
//       gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

//       for (int x=0; x<src.width(); ++x)
//   {
//           (*dst_it) = (src_loc[above] - src_loc[below])/2;
//           ++dst_it;
//           ++src_loc.x();
//       }
//       src_loc+=point2<std::ptrdiff_t>(-src.width(),1);
//   }
// }


// template <typename SrcView, typename DstView>
// void x_gradient(const SrcView& src, const DstView& dst)
// {
//   for (int y=0; y<src.height(); ++y)
//   {
//       typename SrcView::x_iterator src_it = src.row_begin(y);
//       typename DstView::x_iterator dst_it = dst.row_begin(y);

//       for (int x=1; x<src.width()-1; ++x)
//           for (int c=0; c<num_channels<SrcView>::value; ++c)
//               dst_it[x][c] = (src_it[x-1][c]- src_it[x+1][c])/2;
//   }
// }

void y_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
{
  for (int y=1; y<src.height()-1; ++y)
  {
      gray8c_view_t::x_iterator src1_it = src.row_begin(y-1);
      gray8c_view_t::x_iterator src2_it = src.row_begin(y+1);
      gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

      for (int x=0; x<src.width(); ++x) {
          *dst_it = ((*src1_it) - (*src2_it))/2;
          ++dst_it;
          ++src1_it;
          ++src2_it;
      }
  }
}


template <typename Out>
struct halfdiff_cast_channels
{
  template <typename T> Out operator()(const T& in1, const T& in2) const
  {
      return Out((in1-in2)/2);
  }
};

template <typename SrcView, typename DstView>
void x_gradient(const SrcView& src, const DstView& dst)
{
  typedef typename channel_type<DstView>::type dst_channel_t;

  for (int y=0; y<src.height(); ++y)
  {
      typename SrcView::x_iterator src_it = src.row_begin(y);
      typename DstView::x_iterator dst_it = dst.row_begin(y);

      for (int x=1; x<src.width()-1; ++x)
          static_transform(src_it[x-1], src_it[x+1], dst_it[x],
                             halfdiff_cast_channels<dst_channel_t>());
  }
}

void XGradientGray16_Gray32(const unsigned short* src_pixels, ptrdiff_t src_row_bytes, int w, int h,
                            signed int* dst_pixels, ptrdiff_t dst_row_bytes)
{
  gray16c_view_t src=interleaved_view(w,h,(const gray16_pixel_t*)src_pixels,src_row_bytes);
  gray32s_view_t dst=interleaved_view(w,h,(     gray32s_pixel_t*)dst_pixels,dst_row_bytes);
  x_gradient(src,dst);
}

// Calling with 8-bit RGB data into 16-bit BGR
void XGradientRGB8_BGR16(const unsigned char* src_pixels, ptrdiff_t src_row_bytes, int w, int h,
                         signed short* dst_pixels, ptrdiff_t dst_row_bytes)
{
  rgb8c_view_t  src = interleaved_view(w,h,(const rgb8_pixel_t*)src_pixels,src_row_bytes);
  rgb16s_view_t dst = interleaved_view(w,h,(    rgb16s_pixel_t*)dst_pixels,dst_row_bytes);
  x_gradient(src,dst);
}

// Either or both the source and the destination could be planar - the gradient code does not change
void XGradientPlanarRGB8_RGB32(
         const unsigned short* src_r, const unsigned short* src_g, const unsigned short* src_b,
         ptrdiff_t src_row_bytes, int w, int h,
         signed int* dst_pixels, ptrdiff_t dst_row_bytes)
{
  rgb16c_planar_view_t src=planar_rgb_view (w,h, src_r,src_g,src_b,         src_row_bytes);
  rgb32s_view_t        dst=interleaved_view(w,h,(rgb32s_pixel_t*)dst_pixels,dst_row_bytes);
  x_gradient(src,dst);
}

template <typename SrcView, typename DstView>
void y_gradient(const SrcView& src, const DstView& dst)
{
  x_gradient(rotated90ccw_view(src), rotated90ccw_view(dst));
}

template <typename SrcView, typename DstView>
void nth_channel_x_gradient(const SrcView& src, int n, const DstView& dst)
{
  x_gradient(nth_channel_view(src, n), dst);
}

// y_gradient(subsampled_view(nth_channel_view(src, 1), 2,2), dst);

// void x_gradient_unguarded(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   for (int y=0; y<src.height(); ++y)
//   {
//       gray8c_view_t::x_iterator src_it = src.row_begin(y);
//       gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

//       for (int x=0; x<src.width(); ++x)
//           dst_it[x] = (src_it[x-1] - src_it[x+1]) / 2;
//   }
// }

void x_gradient_unguarded(const gray8c_view_t& src, const gray8s_view_t& dst)
{
  gray8c_view_t::iterator src_it = src.begin();
  for (gray8s_view_t::iterator dst_it = dst.begin(); dst_it!=dst.end(); ++dst_it, ++src_it)
      *dst_it = (src_it.x()[-1] - src_it.x()[1]) / 2;
}

// void x_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   assert(src.width()>=2);
//   x_gradient_unguarded(subimage_view(src, 1, 0, src.width()-2, src.height()),
//                        subimage_view(dst, 1, 0, src.width()-2, src.height()));
// }

// struct half_x_difference
// {
//   int operator()(const gray8c_loc_t& src_loc) const
//   {
//       return (src_loc.x()[-1] - src_loc.x()[1]) / 2;
//   }
// };

// void x_gradient_unguarded(const gray8c_view_t& src, const gray8s_view_t& dst)
// {
//   transform_pixel_positions(src, dst, half_x_difference());
// }


void x_gradient_rgb_luminosity(const rgb32fc_view_t& src, const gray8s_view_t& dst)
{
  x_gradient(color_converted_view<gray8_pixel_t>(src), dst);
}


template <typename SrcView, typename DstView>
void x_luminosity_gradient(const SrcView& src, const DstView& dst)
{
  typedef pixel<typename channel_type<SrcView>::type, gray_layout_t> gray_pixel_t;
  x_gradient(color_converted_view<gray_pixel_t>(src), dst);
}

// void x_luminosity_gradient(const rgb32fc_view_t& src, const gray8s_view_t& dst)
// {
//   gray8_image_t ccv_image(src.dimensions());
//   copy_pixels(color_converted_view<gray8_pixel_t>(src), view(ccv_image));

//   x_gradient(const_view(ccv_image), dst);
// }

// template <typename SrcView, typename DstView>
// void x_luminosity_gradient(const SrcView& src, const DstView& dst)
// {
//   typedef typename channel_type<DstView>::type d_channel_t;
//   typedef typename channel_convert_to_unsigned<d_channel_t>::type channel_t;
//   typedef pixel<channel_t, gray_layout_t>  gray_pixel_t;
//   typedef image<gray_pixel_t, false>       gray_image_t;

//   gray_image_t ccv_image(src.dimensions());
//   copy_pixels(color_converted_view<gray_pixel_t>(src), view(ccv_image));
//   x_gradient(const_view(ccv_image), dst);
// }

// template <typename SrcView, typename DstView>
// void x_luminosity_gradient(const SrcView& src, const DstView& dst)
// {
//   typedef typename channel_type<DstView>::type d_channel_t;
//   typedef typename channel_convert_to_unsigned<d_channel_t>::type channel_t;
//   typedef typename image_type<channel_t, gray_layout_t>::type gray_image_t;
//   typedef typename gray_image_t::value_type gray_pixel_t;

//   gray_image_t ccv_image(src.dimensions());
//   copy_and_convert_pixels(src, view(ccv_image));
//   x_gradient(const_view(ccv_image), dst);
// }


// models PixelDereferenceAdaptorConcept
struct mandelbrot_fn
{
  typedef point2<ptrdiff_t>   point_t;

  typedef mandelbrot_fn       const_t;
  typedef gray8_pixel_t       value_type;
  typedef value_type          reference;
  typedef value_type          const_reference;
  typedef point_t             argument_type;
  typedef reference           result_type;
  BOOST_STATIC_CONSTANT(bool, is_mutable=false);

  mandelbrot_fn() {}
  mandelbrot_fn(const point_t& sz) : _img_size(sz) {}

  result_type operator()(const point_t& p) const
  {
      // normalize the coords to (-2..1, -1.5..1.5)
      double t=get_num_iter(point2<double>(p.x/(double)_img_size.x*3-2, p.y/(double)_img_size.y*3-1.5f));
      return value_type((bits8)(pow(t,0.2)*255));   // raise to power suitable for viewing
  }
private:
  point_t _img_size;

  double get_num_iter(const point2<double>& p) const
  {
      point2<double> Z(0,0);
      for (int i=0; i<100; ++i)  // 100 iterations
  {
          Z = point2<double>(Z.x*Z.x - Z.y*Z.y + p.x, 2*Z.x*Z.y + p.y);
          if (Z.x*Z.x + Z.y*Z.y > 4)
              return i/(double)100;
      }
      return 0;
  }
};

int main() {
	typedef mandelbrot_fn::point_t point_t;
	typedef virtual_2d_locator<mandelbrot_fn,false> locator_t;
	typedef image_view<locator_t> my_virt_view_t;

	point_t dims(200,200);

	// Construct a Mandelbrot view with a locator, taking top-left corner (0,0) and step (1,1)
	my_virt_view_t mandel(dims, locator_t(point_t(0,0), point_t(1,1), mandelbrot_fn(dims)));

	gray8s_image_t img(dims);
	x_gradient(rotated90cw_view(mandel), view(img));

	// Save the Mandelbrot set and its 90-degree rotated gradient (jpeg cannot save signed char; must convert to unsigned char)
	jpeg_write_view("mandel.jpg",mandel);
	jpeg_write_view("mandel_grad.jpg",color_converted_view<gray8_pixel_t>(const_view(img)));
}