
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1020.95 | 0.0455208 | 126.367ms | 1313 | 80 | 24.9361 | 1226.47 | 0.0285289 | 2.37608 | 1(Win) | true |
| simdjson (ondemand) | 358.614 | 0.150197 | 358.063ms | 1313 | 4890 | 134495 | 3491.71 | 0.331805 | 6.85336 | 2(Loss) | true |
