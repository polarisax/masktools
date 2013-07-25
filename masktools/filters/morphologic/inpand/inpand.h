#ifndef __Mt_Inpand_H__
#define __Mt_Inpand_H__

#include "../morphologic.h"

namespace Filtering { namespace MaskTools { namespace Filters { namespace Morphologic { namespace Inpand {


extern Processor *inpand_square_c;
extern Processor *inpand_square_sse2;
extern Processor *inpand_square_asse2;

extern Processor *inpand_horizontal_c;
extern Processor *inpand_horizontal_sse2;
extern Processor *inpand_horizontal_asse2;

extern Processor *inpand_vertical_c;
extern Processor *inpand_vertical_sse2;
extern Processor *inpand_vertical_asse2;

extern Processor *inpand_both_c;
extern Processor *inpand_both_sse2;
extern Processor *inpand_both_asse2;

extern Processor *inpand_custom_c;

class Inpand : public Morphologic::MorphologicFilter
{
public:
   Inpand(const Parameters&parameters) : Morphologic::MorphologicFilter( parameters )
   {
      /* add the processors */
      if ( parameters["mode"].toString() == "square" )
      {
         processors.push_back(Filtering::Processor<Processor>(inpand_square_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(inpand_square_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 3));
         processors.push_back(Filtering::Processor<Processor>(inpand_square_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 4));
      }
      else if ( parameters["mode"].toString() == "horizontal" )
      {
         processors.push_back(Filtering::Processor<Processor>(inpand_horizontal_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(inpand_horizontal_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 3));
         processors.push_back(Filtering::Processor<Processor>(inpand_horizontal_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 4));
      }
      else if ( parameters["mode"].toString() == "vertical" )
      {
         processors.push_back(Filtering::Processor<Processor>(inpand_vertical_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(inpand_vertical_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 3));
         processors.push_back(Filtering::Processor<Processor>(inpand_vertical_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 4));
      }
      else if ( parameters["mode"].toString() == "both" )
      {
         processors.push_back(Filtering::Processor<Processor>(inpand_both_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(inpand_both_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 3));
         processors.push_back(Filtering::Processor<Processor>(inpand_both_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 4));
      }
      else
      {
         processors.push_back(Filtering::Processor<Processor>(inpand_custom_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         FillCoordinates( parameters["mode"].toString() );
      }
   }

   static Signature Inpand::filter_signature()
   {
      Signature signature = "mt_inpand";

      signature.add( Parameter( TYPE_CLIP, "" ) );
      signature.add( Parameter( 255, "thY" ) );
      signature.add( Parameter( 255, "thC" ) );
      signature.add( Parameter( String( "square" ), "mode" ) );

      return add_defaults( signature );
   }
};

} } } } } // namespace Inpand, Morphologic, Filter, MaskTools, Filtering

#endif