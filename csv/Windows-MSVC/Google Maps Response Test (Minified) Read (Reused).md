
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1423.28 | 0.386789 | 896.838ms | 11812 | 640 | 599784 | 7914.69 | 0.126507 | 1.7334 | 1(Win) | true |
| Jsonifier (two-stage) | 1213.23 | 0.214464 | 1030.64ms | 11812 | 2560 | 1.0151e+06 | 9284.96 | 0.0467203 | 2.03421 | 2(Loss) | true |
| Glaze | 964.814 | 0.339275 | 1309.8ms | 11812 | 640 | 1.00426e+06 | 11675.6 | 0.142057 | 2.55978 | 3(Loss) | true |
| simdjson (ondemand) | 580.515 | 0.368802 | 2084.1ms | 11812 | 640 | 3.27783e+06 | 19404.8 | 0.812566 | 4.25893 | 4(Loss) | true |
