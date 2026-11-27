
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 948.455 | 0.0598806 | 135.12ms | 1313 | 40 | 24.9994 | 1320.22 | 0.0423087 | 2.55885 | 1(Win) | true |
| simdjson (ondemand) | 355.207 | 0.0284924 | 357.116ms | 1313 | 160 | 161.415 | 3525.19 | 0.0494898 | 6.91882 | 2(Loss) | true |
