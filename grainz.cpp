#include "grainz.h"

namespace grainz {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_samplebufferone_1;
	Data m_samplebuffertwo_2;
	int __exception;
	int vectorsize;
	t_sample __m_carry_10;
	t_sample __m_carry_15;
	t_sample __m_count_13;
	t_sample __m_count_8;
	t_sample __m_carry_5;
	t_sample __m_count_3;
	t_sample __m_count_18;
	t_sample samplerate;
	t_sample __m_carry_20;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_samplebufferone_1.reset("samplebufferone", ((int)132300), ((int)2));
		m_samplebuffertwo_2.reset("samplebuffertwo", ((int)132300), ((int)2));
		__m_count_3 = 0;
		__m_carry_5 = 0;
		__m_count_8 = 0;
		__m_carry_10 = 0;
		__m_count_13 = 0;
		__m_carry_15 = 0;
		__m_count_18 = 0;
		__m_carry_20 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int samplebuffertwo_dim = m_samplebuffertwo_2.dim;
		int samplebuffertwo_channels = m_samplebuffertwo_2.channels;
		int dim_10 = samplebuffertwo_dim;
		int samplebufferone_dim = m_samplebufferone_1.dim;
		int samplebufferone_channels = m_samplebufferone_1.channels;
		int dim_18 = samplebufferone_dim;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			__m_count_3 = (((int)0) ? 0 : (fixdenorm(__m_count_3 + ((int)1))));
			int carry_4 = 0;
			if ((((int)0) != 0)) {
				__m_count_3 = 0;
				__m_carry_5 = 0;
				
			} else if (((dim_10 > 0) && (__m_count_3 >= dim_10))) {
				int wraps_6 = (__m_count_3 / dim_10);
				__m_carry_5 = (__m_carry_5 + wraps_6);
				__m_count_3 = (__m_count_3 - (wraps_6 * dim_10));
				carry_4 = 1;
				
			};
			int counter_13 = __m_count_3;
			int counter_14 = carry_4;
			int counter_15 = __m_carry_5;
			bool index_ignore_7 = ((counter_13 >= samplebuffertwo_dim) || (counter_13 < 0));
			if ((!index_ignore_7)) {
				m_samplebuffertwo_2.write(in2, counter_13, 0);
				
			};
			__m_count_8 = (((int)0) ? 0 : (fixdenorm(__m_count_8 + ((int)1))));
			int carry_9 = 0;
			if ((((int)0) != 0)) {
				__m_count_8 = 0;
				__m_carry_10 = 0;
				
			} else if (((dim_10 > 0) && (__m_count_8 >= dim_10))) {
				int wraps_11 = (__m_count_8 / dim_10);
				__m_carry_10 = (__m_carry_10 + wraps_11);
				__m_count_8 = (__m_count_8 - (wraps_11 * dim_10));
				carry_9 = 1;
				
			};
			int counter_3 = __m_count_8;
			int counter_4 = carry_9;
			int counter_5 = __m_carry_10;
			bool index_ignore_12 = ((counter_3 >= samplebuffertwo_dim) || (counter_3 < 0));
			// samples samplebuffertwo channel 1;
			t_sample sample_samplebuffertwo_6 = (index_ignore_12 ? 0 : m_samplebuffertwo_2.read(counter_3, 0));
			t_sample index_samplebuffertwo_7 = counter_3;
			t_sample out2 = sample_samplebuffertwo_6;
			__m_count_13 = (((int)0) ? 0 : (fixdenorm(__m_count_13 + ((int)1))));
			int carry_14 = 0;
			if ((((int)0) != 0)) {
				__m_count_13 = 0;
				__m_carry_15 = 0;
				
			} else if (((dim_18 > 0) && (__m_count_13 >= dim_18))) {
				int wraps_16 = (__m_count_13 / dim_18);
				__m_carry_15 = (__m_carry_15 + wraps_16);
				__m_count_13 = (__m_count_13 - (wraps_16 * dim_18));
				carry_14 = 1;
				
			};
			int counter_28 = __m_count_13;
			int counter_29 = carry_14;
			int counter_30 = __m_carry_15;
			bool index_ignore_17 = ((counter_28 >= samplebufferone_dim) || (counter_28 < 0));
			if ((!index_ignore_17)) {
				m_samplebufferone_1.write(in1, counter_28, 0);
				
			};
			__m_count_18 = (((int)0) ? 0 : (fixdenorm(__m_count_18 + ((int)1))));
			int carry_19 = 0;
			if ((((int)0) != 0)) {
				__m_count_18 = 0;
				__m_carry_20 = 0;
				
			} else if (((dim_18 > 0) && (__m_count_18 >= dim_18))) {
				int wraps_21 = (__m_count_18 / dim_18);
				__m_carry_20 = (__m_carry_20 + wraps_21);
				__m_count_18 = (__m_count_18 - (wraps_21 * dim_18));
				carry_19 = 1;
				
			};
			int counter_21 = __m_count_18;
			int counter_22 = carry_19;
			int counter_23 = __m_carry_20;
			bool index_ignore_22 = ((counter_21 >= samplebufferone_dim) || (counter_21 < 0));
			// samples samplebufferone channel 1;
			t_sample sample_samplebufferone_24 = (index_ignore_22 ? 0 : m_samplebufferone_1.read(counter_21, 0));
			t_sample index_samplebufferone_25 = counter_21;
			t_sample out1 = sample_samplebufferone_24;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_samplebufferone(void * _value) {
		m_samplebufferone_1.setbuffer(_value);
	};
	inline void set_samplebuffertwo(void * _value) {
		m_samplebuffertwo_2.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 2; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_samplebufferone(ref); break;
		case 1: self->set_samplebuffertwo(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(2 * sizeof(ParamInfo));
	self->__commonstate.numparams = 2;
	// initialize parameter 0 ("m_samplebufferone_1")
	pi = self->__commonstate.params + 0;
	pi->name = "samplebufferone";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_samplebuffertwo_2")
	pi = self->__commonstate.params + 1;
	pi->name = "samplebuffertwo";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // grainz::
