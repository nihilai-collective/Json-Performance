
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5068.33 | 0.127266 | 778.67ms | 3873 | 4890 | 4206.25 | 728.756 | 0.202872 | 1.08024 | 5.29176 | 0.530855 | 0.000769841 | 2.76678e-05 | 1.79524e-06 | 1(Win) | true |
| simdjson (stage-1) | 1932.52 | 0.0373002 | 904.245ms | 3873 | 4890 | 2485.28 | 1911.27 | 0.00837318 | 2.71816 | 14.3145 | 1.14821 | 0.000621945 | 4.93163e-05 | 1.41507e-05 | 2(Loss) | true |
