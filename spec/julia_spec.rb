require 'spec_helper'

describe Julia do
  it 'has a version number' do
    expect(Julia::VERSION).not_to be nil
  end

  describe '.eval' do
    def jl_eval(src)
      Julia.eval(src)
    end

    def expect_julia(src)
      expect(jl_eval(src))
    end

    # Boolean conversion

    specify { expect_julia('true').to equal(true) }
    specify { expect_julia('false').to equal(false) }

    # Integer conversion

    specify { expect_julia('1').to eq(1) }
    specify { expect_julia('Int8(1)').to eq(1) }
    specify { expect_julia('UInt8(1)').to eq(1) }
    specify { expect_julia('Int16(1)').to eq(1) }
    specify { expect_julia('UInt16(1)').to eq(1) }
    specify { expect_julia('Int32(1)').to eq(1) }
    specify { expect_julia('UInt32(1)').to eq(1) }
    specify { expect_julia('Int64(1)').to eq(1) }
    specify { expect_julia('UInt64(1)').to eq(1) }
    specify { expect_julia('Int128(1)').to eq(1) }
    specify { expect_julia('UInt128(1)').to eq(1) }
    specify { expect_julia('BigInt(1)').to eq(1) }
  end
end
