
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 796.344 | 0.0330276 | 459.391ms | 3862 | 40 | 93.3333 | 4625 | 0.00720773 | 3.09043 | 1(Win) | true |
| simdjson (ondemand) | 547.266 | 0.161394 | 673.001ms | 3862 | 2560 | 302026 | 6729.99 | 0.48703 | 4.50542 | 2(Loss) | true |
