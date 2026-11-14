
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4976.57 | 0.127635 | 781.654ms | 3862 | 4890 | 4363.29 | 740.086 | 0.221002 | 1.09433 | 5.31978 | 0.535474 | 0.00121815 | 4.71799e-05 | 1.57266e-05 | 1(Win) | true |
| simdjson (stage-1) | 1915.16 | 0.0725445 | 907.835ms | 3862 | 320 | 622.835 | 1923.12 | 0.131632 | 2.74707 | 14.3553 | 1.15148 | 0.000641669 | 3.3985e-05 | 8.90083e-06 | 2(Loss) | true |
