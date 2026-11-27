
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2640.15 | 0.0804348 | 50.1281ms | 1313 | 160 | 23.2852 | 474.281 | 0.0355675 | 0.887876 | 1(Win) | true |
| simdjson (stage-1) | 1275.78 | 0.085138 | 101.328ms | 1313 | 30 | 20.9483 | 981.5 | 0.0339501 | 1.88903 | 2(Loss) | true |
