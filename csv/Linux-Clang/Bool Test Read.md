
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1198.05 | 0.0492712 | 780.303ms | 905 | 4890 | 616.091 | 720.402 | 0.292749 | 4.53714 | 22.9392 | 2.29503 | 0.00450689 | 5.89771e-05 | 4.97125e-06 | 1(Win) | true |
| simdjson (stage-1) | 448.728 | 0.0489501 | 913.063ms | 905 | 4890 | 4334.57 | 1923.38 | 0.00477054 | 11.6911 | 61.2597 | 4.91381 | 0.0029475 | 8.13477e-05 | 1.46878e-05 | 2(Loss) | true |
