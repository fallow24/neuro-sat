#ifndef OPTIMIZER_SGD_H_
#define OPTIMIZER_SGD_H_

#include "lib/Eigen/Core"
//#include "lib/Eigen/Core"
#include "../Config.h"
#include "../Optimizer.h"

namespace MiniDNN
{


///
/// \ingroup Optimizers
///
/// The Stochastic Gradient Descent (SGD) algorithm
///
class SGD: public Optimizer
{
    private:
        typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
        typedef Vector::ConstAlignedMapType ConstAlignedMapVec;
        typedef Vector::AlignedMapType AlignedMapVec;

    public:
        //Scalar m_lrate;
        Scalar m_decay;

        SGD() :
            m_decay(Scalar(0))
        {
            m_lrate = 0.01;
        }

        void update(ConstAlignedMapVec& dvec, AlignedMapVec& vec)
        {
            vec.noalias() -= m_lrate * (dvec + m_decay * vec);
        }
};


} // namespace MiniDNN


#endif /* OPTIMIZER_SGD_H_ */
