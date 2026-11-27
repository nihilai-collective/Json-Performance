
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15947.4 | 0.041481 | 1465.76ms | 124597 | 30 | 286.585 | 7451.03 | 0.0429286 | 0.324891 | 1.68016 | 0.0881241 | 2.46127e-05 | 5.35058e-07 | 0 | 1(Win) | true |
| simdjson (stage-1) | 14746.3 | 0.0933757 | 1526.17ms | 124597 | 160 | 9058.1 | 8057.96 | 0.0172996 | 0.350756 | 1.8435 | 0.0692474 | 1.84094e-05 | 4.36407e-06 | 3.11003e-06 | 2(Loss) | true |
