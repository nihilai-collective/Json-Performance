
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4672.44 | 0.107703 | 82.127ms | 3862 | 640 | 461.287 | 788.258 | 0.23237 | 0.511857 | 1(Win) | true |
| simdjson (stage-1) | 2215.57 | 0.0528242 | 170.147ms | 3862 | 160 | 123.379 | 1662.37 | 0.00714291 | 1.10048 | 2(Loss) | true |
