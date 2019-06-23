#-------------------------------------------------
#
# Project created by QtCreator 2019-05-13T15:41:08
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SatSimApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 console

SOURCES += \
        controller/controller.cpp \
        controller/dnn.cpp \
        controller/parseexcept.cpp \
        controller/pid.cpp \
        controller/sample.cpp \
        controller/samplegenerator.cpp \
        main.cpp \
        satellite/complexsat.cpp \
        satellite/cubesat.cpp \
        satellite/satellite.cpp \
        satellite/wheel.cpp \
        simulation/command.cpp \
        simulation/controlledsim.cpp \
        simulation/instructedsim.cpp \
        simulation/instruction.cpp \
        simulation/invdimexcept.cpp \
        simulation/simulation.cpp \
        ui/preferences.cpp \
        ui/samplewizzard.cpp \
        ui/satsimapp.cpp \
        ui/commanddialog.cpp \
        ui/progress.cpp \
        qcustomplot.cpp \
        ui/trainwizzard.cpp \
        ui/wheeldialog.cpp

HEADERS += \
        ui/commanddialog.h \
        controller/controller.h \
        controller/dnn.h \
        controller/parseexcept.h \
        controller/pid.h \
        controller/sample.h \
        controller/samplegenerator.h \
        lib/Eigen/Cholesky \
        lib/Eigen/CholmodSupport \
        lib/Eigen/Core \
        lib/Eigen/Dense \
        lib/Eigen/Eigen \
        lib/Eigen/Eigenvalues \
        lib/Eigen/Geometry \
        lib/Eigen/Householder \
        lib/Eigen/IterativeLinearSolvers \
        lib/Eigen/Jacobi \
        lib/Eigen/LU \
        lib/Eigen/MetisSupport \
        lib/Eigen/OrderingMethods \
        lib/Eigen/PaStiXSupport \
        lib/Eigen/PardisoSupport \
        lib/Eigen/QR \
        lib/Eigen/QtAlignedMalloc \
        lib/Eigen/SPQRSupport \
        lib/Eigen/SVD \
        lib/Eigen/Sparse \
        lib/Eigen/SparseCholesky \
        lib/Eigen/SparseCore \
        lib/Eigen/SparseLU \
        lib/Eigen/SparseQR \
        lib/Eigen/StdDeque \
        lib/Eigen/StdList \
        lib/Eigen/StdVector \
        lib/Eigen/SuperLUSupport \
        lib/Eigen/UmfPackSupport \
        lib/Eigen/src/Cholesky/LDLT.h \
        lib/Eigen/src/Cholesky/LLT.h \
        lib/Eigen/src/Cholesky/LLT_LAPACKE.h \
        lib/Eigen/src/CholmodSupport/CholmodSupport.h \
        lib/Eigen/src/Core/Array.h \
        lib/Eigen/src/Core/ArrayBase.h \
        lib/Eigen/src/Core/ArrayWrapper.h \
        lib/Eigen/src/Core/Assign.h \
        lib/Eigen/src/Core/AssignEvaluator.h \
        lib/Eigen/src/Core/Assign_MKL.h \
        lib/Eigen/src/Core/BandMatrix.h \
        lib/Eigen/src/Core/Block.h \
        lib/Eigen/src/Core/BooleanRedux.h \
        lib/Eigen/src/Core/CommaInitializer.h \
        lib/Eigen/src/Core/ConditionEstimator.h \
        lib/Eigen/src/Core/CoreEvaluators.h \
        lib/Eigen/src/Core/CoreIterators.h \
        lib/Eigen/src/Core/CwiseBinaryOp.h \
        lib/Eigen/src/Core/CwiseNullaryOp.h \
        lib/Eigen/src/Core/CwiseTernaryOp.h \
        lib/Eigen/src/Core/CwiseUnaryOp.h \
        lib/Eigen/src/Core/CwiseUnaryView.h \
        lib/Eigen/src/Core/DenseBase.h \
        lib/Eigen/src/Core/DenseCoeffsBase.h \
        lib/Eigen/src/Core/DenseStorage.h \
        lib/Eigen/src/Core/Diagonal.h \
        lib/Eigen/src/Core/DiagonalMatrix.h \
        lib/Eigen/src/Core/DiagonalProduct.h \
        lib/Eigen/src/Core/Dot.h \
        lib/Eigen/src/Core/EigenBase.h \
        lib/Eigen/src/Core/ForceAlignedAccess.h \
        lib/Eigen/src/Core/Fuzzy.h \
        lib/Eigen/src/Core/GeneralProduct.h \
        lib/Eigen/src/Core/GenericPacketMath.h \
        lib/Eigen/src/Core/GlobalFunctions.h \
        lib/Eigen/src/Core/IO.h \
        lib/Eigen/src/Core/Inverse.h \
        lib/Eigen/src/Core/Map.h \
        lib/Eigen/src/Core/MapBase.h \
        lib/Eigen/src/Core/MathFunctions.h \
        lib/Eigen/src/Core/MathFunctionsImpl.h \
        lib/Eigen/src/Core/Matrix.h \
        lib/Eigen/src/Core/MatrixBase.h \
        lib/Eigen/src/Core/NestByValue.h \
        lib/Eigen/src/Core/NoAlias.h \
        lib/Eigen/src/Core/NumTraits.h \
        lib/Eigen/src/Core/PermutationMatrix.h \
        lib/Eigen/src/Core/PlainObjectBase.h \
        lib/Eigen/src/Core/Product.h \
        lib/Eigen/src/Core/ProductEvaluators.h \
        lib/Eigen/src/Core/Random.h \
        lib/Eigen/src/Core/Redux.h \
        lib/Eigen/src/Core/Ref.h \
        lib/Eigen/src/Core/Replicate.h \
        lib/Eigen/src/Core/ReturnByValue.h \
        lib/Eigen/src/Core/Reverse.h \
        lib/Eigen/src/Core/Select.h \
        lib/Eigen/src/Core/SelfAdjointView.h \
        lib/Eigen/src/Core/SelfCwiseBinaryOp.h \
        lib/Eigen/src/Core/Solve.h \
        lib/Eigen/src/Core/SolveTriangular.h \
        lib/Eigen/src/Core/SolverBase.h \
        lib/Eigen/src/Core/StableNorm.h \
        lib/Eigen/src/Core/Stride.h \
        lib/Eigen/src/Core/Swap.h \
        lib/Eigen/src/Core/Transpose.h \
        lib/Eigen/src/Core/Transpositions.h \
        lib/Eigen/src/Core/TriangularMatrix.h \
        lib/Eigen/src/Core/VectorBlock.h \
        lib/Eigen/src/Core/VectorwiseOp.h \
        lib/Eigen/src/Core/Visitor.h \
        lib/Eigen/src/Core/arch/AVX/Complex.h \
        lib/Eigen/src/Core/arch/AVX/MathFunctions.h \
        lib/Eigen/src/Core/arch/AVX/PacketMath.h \
        lib/Eigen/src/Core/arch/AVX/TypeCasting.h \
        lib/Eigen/src/Core/arch/AVX512/MathFunctions.h \
        lib/Eigen/src/Core/arch/AVX512/PacketMath.h \
        lib/Eigen/src/Core/arch/AltiVec/Complex.h \
        lib/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
        lib/Eigen/src/Core/arch/AltiVec/PacketMath.h \
        lib/Eigen/src/Core/arch/CUDA/Complex.h \
        lib/Eigen/src/Core/arch/CUDA/Half.h \
        lib/Eigen/src/Core/arch/CUDA/MathFunctions.h \
        lib/Eigen/src/Core/arch/CUDA/PacketMath.h \
        lib/Eigen/src/Core/arch/CUDA/PacketMathHalf.h \
        lib/Eigen/src/Core/arch/CUDA/TypeCasting.h \
        lib/Eigen/src/Core/arch/Default/ConjHelper.h \
        lib/Eigen/src/Core/arch/Default/Settings.h \
        lib/Eigen/src/Core/arch/NEON/Complex.h \
        lib/Eigen/src/Core/arch/NEON/MathFunctions.h \
        lib/Eigen/src/Core/arch/NEON/PacketMath.h \
        lib/Eigen/src/Core/arch/SSE/Complex.h \
        lib/Eigen/src/Core/arch/SSE/MathFunctions.h \
        lib/Eigen/src/Core/arch/SSE/PacketMath.h \
        lib/Eigen/src/Core/arch/SSE/TypeCasting.h \
        lib/Eigen/src/Core/arch/ZVector/Complex.h \
        lib/Eigen/src/Core/arch/ZVector/MathFunctions.h \
        lib/Eigen/src/Core/arch/ZVector/PacketMath.h \
        lib/Eigen/src/Core/functors/AssignmentFunctors.h \
        lib/Eigen/src/Core/functors/BinaryFunctors.h \
        lib/Eigen/src/Core/functors/NullaryFunctors.h \
        lib/Eigen/src/Core/functors/StlFunctors.h \
        lib/Eigen/src/Core/functors/TernaryFunctors.h \
        lib/Eigen/src/Core/functors/UnaryFunctors.h \
        lib/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
        lib/Eigen/src/Core/products/GeneralMatrixMatrix.h \
        lib/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
        lib/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
        lib/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
        lib/Eigen/src/Core/products/GeneralMatrixVector.h \
        lib/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
        lib/Eigen/src/Core/products/Parallelizer.h \
        lib/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
        lib/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
        lib/Eigen/src/Core/products/SelfadjointMatrixVector.h \
        lib/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
        lib/Eigen/src/Core/products/SelfadjointProduct.h \
        lib/Eigen/src/Core/products/SelfadjointRank2Update.h \
        lib/Eigen/src/Core/products/TriangularMatrixMatrix.h \
        lib/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
        lib/Eigen/src/Core/products/TriangularMatrixVector.h \
        lib/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
        lib/Eigen/src/Core/products/TriangularSolverMatrix.h \
        lib/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
        lib/Eigen/src/Core/products/TriangularSolverVector.h \
        lib/Eigen/src/Core/util/BlasUtil.h \
        lib/Eigen/src/Core/util/Constants.h \
        lib/Eigen/src/Core/util/DisableStupidWarnings.h \
        lib/Eigen/src/Core/util/ForwardDeclarations.h \
        lib/Eigen/src/Core/util/MKL_support.h \
        lib/Eigen/src/Core/util/Macros.h \
        lib/Eigen/src/Core/util/Memory.h \
        lib/Eigen/src/Core/util/Meta.h \
        lib/Eigen/src/Core/util/NonMPL2.h \
        lib/Eigen/src/Core/util/ReenableStupidWarnings.h \
        lib/Eigen/src/Core/util/StaticAssert.h \
        lib/Eigen/src/Core/util/XprHelper.h \
        lib/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
        lib/Eigen/src/Eigenvalues/ComplexSchur.h \
        lib/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
        lib/Eigen/src/Eigenvalues/EigenSolver.h \
        lib/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
        lib/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
        lib/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
        lib/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
        lib/Eigen/src/Eigenvalues/RealQZ.h \
        lib/Eigen/src/Eigenvalues/RealSchur.h \
        lib/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
        lib/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
        lib/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
        lib/Eigen/src/Eigenvalues/Tridiagonalization.h \
        lib/Eigen/src/Geometry/AlignedBox.h \
        lib/Eigen/src/Geometry/AngleAxis.h \
        lib/Eigen/src/Geometry/EulerAngles.h \
        lib/Eigen/src/Geometry/Homogeneous.h \
        lib/Eigen/src/Geometry/Hyperplane.h \
        lib/Eigen/src/Geometry/OrthoMethods.h \
        lib/Eigen/src/Geometry/ParametrizedLine.h \
        lib/Eigen/src/Geometry/Quaternion.h \
        lib/Eigen/src/Geometry/Rotation2D.h \
        lib/Eigen/src/Geometry/RotationBase.h \
        lib/Eigen/src/Geometry/Scaling.h \
        lib/Eigen/src/Geometry/Transform.h \
        lib/Eigen/src/Geometry/Translation.h \
        lib/Eigen/src/Geometry/Umeyama.h \
        lib/Eigen/src/Geometry/arch/Geometry_SSE.h \
        lib/Eigen/src/Householder/BlockHouseholder.h \
        lib/Eigen/src/Householder/Householder.h \
        lib/Eigen/src/Householder/HouseholderSequence.h \
        lib/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
        lib/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
        lib/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
        lib/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
        lib/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
        lib/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
        lib/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
        lib/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
        lib/Eigen/src/Jacobi/Jacobi.h \
        lib/Eigen/src/LU/Determinant.h \
        lib/Eigen/src/LU/FullPivLU.h \
        lib/Eigen/src/LU/InverseImpl.h \
        lib/Eigen/src/LU/PartialPivLU.h \
        lib/Eigen/src/LU/PartialPivLU_LAPACKE.h \
        lib/Eigen/src/LU/arch/Inverse_SSE.h \
        lib/Eigen/src/MetisSupport/MetisSupport.h \
        lib/Eigen/src/OrderingMethods/Amd.h \
        lib/Eigen/src/OrderingMethods/Eigen_Colamd.h \
        lib/Eigen/src/OrderingMethods/Ordering.h \
        lib/Eigen/src/PaStiXSupport/PaStiXSupport.h \
        lib/Eigen/src/PardisoSupport/PardisoSupport.h \
        lib/Eigen/src/QR/ColPivHouseholderQR.h \
        lib/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
        lib/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
        lib/Eigen/src/QR/FullPivHouseholderQR.h \
        lib/Eigen/src/QR/HouseholderQR.h \
        lib/Eigen/src/QR/HouseholderQR_LAPACKE.h \
        lib/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
        lib/Eigen/src/SVD/BDCSVD.h \
        lib/Eigen/src/SVD/JacobiSVD.h \
        lib/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
        lib/Eigen/src/SVD/SVDBase.h \
        lib/Eigen/src/SVD/UpperBidiagonalization.h \
        lib/Eigen/src/SparseCholesky/SimplicialCholesky.h \
        lib/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
        lib/Eigen/src/SparseCore/AmbiVector.h \
        lib/Eigen/src/SparseCore/CompressedStorage.h \
        lib/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
        lib/Eigen/src/SparseCore/MappedSparseMatrix.h \
        lib/Eigen/src/SparseCore/SparseAssign.h \
        lib/Eigen/src/SparseCore/SparseBlock.h \
        lib/Eigen/src/SparseCore/SparseColEtree.h \
        lib/Eigen/src/SparseCore/SparseCompressedBase.h \
        lib/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
        lib/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
        lib/Eigen/src/SparseCore/SparseDenseProduct.h \
        lib/Eigen/src/SparseCore/SparseDiagonalProduct.h \
        lib/Eigen/src/SparseCore/SparseDot.h \
        lib/Eigen/src/SparseCore/SparseFuzzy.h \
        lib/Eigen/src/SparseCore/SparseMap.h \
        lib/Eigen/src/SparseCore/SparseMatrix.h \
        lib/Eigen/src/SparseCore/SparseMatrixBase.h \
        lib/Eigen/src/SparseCore/SparsePermutation.h \
        lib/Eigen/src/SparseCore/SparseProduct.h \
        lib/Eigen/src/SparseCore/SparseRedux.h \
        lib/Eigen/src/SparseCore/SparseRef.h \
        lib/Eigen/src/SparseCore/SparseSelfAdjointView.h \
        lib/Eigen/src/SparseCore/SparseSolverBase.h \
        lib/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
        lib/Eigen/src/SparseCore/SparseTranspose.h \
        lib/Eigen/src/SparseCore/SparseTriangularView.h \
        lib/Eigen/src/SparseCore/SparseUtil.h \
        lib/Eigen/src/SparseCore/SparseVector.h \
        lib/Eigen/src/SparseCore/SparseView.h \
        lib/Eigen/src/SparseCore/TriangularSolver.h \
        lib/Eigen/src/SparseLU/SparseLU.h \
        lib/Eigen/src/SparseLU/SparseLUImpl.h \
        lib/Eigen/src/SparseLU/SparseLU_Memory.h \
        lib/Eigen/src/SparseLU/SparseLU_Structs.h \
        lib/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
        lib/Eigen/src/SparseLU/SparseLU_Utils.h \
        lib/Eigen/src/SparseLU/SparseLU_column_bmod.h \
        lib/Eigen/src/SparseLU/SparseLU_column_dfs.h \
        lib/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
        lib/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
        lib/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
        lib/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
        lib/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
        lib/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
        lib/Eigen/src/SparseLU/SparseLU_pivotL.h \
        lib/Eigen/src/SparseLU/SparseLU_pruneL.h \
        lib/Eigen/src/SparseLU/SparseLU_relax_snode.h \
        lib/Eigen/src/SparseQR/SparseQR.h \
        lib/Eigen/src/StlSupport/StdDeque.h \
        lib/Eigen/src/StlSupport/StdList.h \
        lib/Eigen/src/StlSupport/StdVector.h \
        lib/Eigen/src/StlSupport/details.h \
        lib/Eigen/src/SuperLUSupport/SuperLUSupport.h \
        lib/Eigen/src/UmfPackSupport/UmfPackSupport.h \
        lib/Eigen/src/misc/Image.h \
        lib/Eigen/src/misc/Kernel.h \
        lib/Eigen/src/misc/RealSvd2x2.h \
        lib/Eigen/src/misc/blas.h \
        lib/Eigen/src/misc/lapack.h \
        lib/Eigen/src/misc/lapacke.h \
        lib/Eigen/src/misc/lapacke_mangling.h \
        lib/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
        lib/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
        lib/Eigen/src/plugins/BlockMethods.h \
        lib/Eigen/src/plugins/CommonCwiseBinaryOps.h \
        lib/Eigen/src/plugins/CommonCwiseUnaryOps.h \
        lib/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
        lib/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
        lib/MiniDNN/Activation/Identity.h \
        lib/MiniDNN/Activation/ReLU.h \
        lib/MiniDNN/Activation/Sigmoid.h \
        lib/MiniDNN/Activation/Softmax.h \
        lib/MiniDNN/Callback.h \
        lib/MiniDNN/Callback/VerboseCallback.h \
        lib/MiniDNN/Config.h \
        lib/MiniDNN/EigenStream.h \
        lib/MiniDNN/Layer.h \
        lib/MiniDNN/Layer/Convolutional.h \
        lib/MiniDNN/Layer/FullyConnected.h \
        lib/MiniDNN/Layer/MaxPooling.h \
        lib/MiniDNN/M_Assert.h \
        lib/MiniDNN/MiniDNN.h \
        lib/MiniDNN/Network.h \
        lib/MiniDNN/Optimizer.h \
        lib/MiniDNN/Optimizer/AdaGrad.h \
        lib/MiniDNN/Optimizer/RMSProp.h \
        lib/MiniDNN/Optimizer/SGD.h \
        lib/MiniDNN/Output.h \
        lib/MiniDNN/Output/BinaryClassEntropy.h \
        lib/MiniDNN/Output/MultiClassEntropy.h \
        lib/MiniDNN/Output/RegressionMSE.h \
        lib/MiniDNN/RNG.h \
        lib/MiniDNN/Utils/Convolution.h \
        lib/MiniDNN/Utils/FindMax.h \
        lib/MiniDNN/Utils/Random.h \
        lib/MiniDNN/Utils/sparsepp.h \
        ui/preferences.h \
        ui/progress.h \
        qcustomplot.h \
        satellite/complexsat.h \
        satellite/cubesat.h \
        satellite/satellite.h \
        satellite/wheel.h \
        satellitesimulation.h \
        ui/samplewizzard.h \
        ui/satsimapp.h \
        simulation/command.h \
        simulation/controlledsim.h \
        simulation/instructedsim.h \
        simulation/instruction.h \
        simulation/invdimexcept.h \
        simulation/simulation.h \
        ui/trainwizzard.h \
        utils.h \
        ui/wheeldialog.h

FORMS += \
        ui/layout/commanddialog.ui \
        ui/layout/preferences.ui \
        ui/layout/progress.ui \
        ui/layout/satsimapp.ui \
        ui/layout/trainwizzard.ui \
        ui/layout/wheeldialog.ui \
        ui/layout/samplewizzard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../usr/local/include/eigen3/signature_of_eigen3_matrix_library \
    lib/Eigen/CMakeLists.txt
