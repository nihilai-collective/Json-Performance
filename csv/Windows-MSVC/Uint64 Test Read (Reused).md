
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 611.578 | 0.136195 | 609.369ms | 3873 | 4890 | 330844 | 6039.43 | 0.151545 | 4.03064 | 1(Win) | true |
| simdjson (ondemand) | 316.011 | 0.226107 | 1165.69ms | 3873 | 320 | 223495 | 11688.1 | 0.378223 | 7.81638 | 2(Loss) | true |
