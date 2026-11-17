
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1439.17 | 0.0166634 | 8266.76ms | 94653 | 4890 | 534171 | 62722.5 | 0.163941 | 3.51841 | 16.8554 | 3.34383 | 0.00779316 | 7.44513e-06 | 3.34879e-06 | 1(Win) | true |
| simdjson (ondemand) | 812.31 | 0.0331881 | 6708.15ms | 94653 | 1280 | 1.741e+06 | 111125 | 0.0946126 | 6.22536 | 30.3784 | 6.20564 | 0.0105151 | 2.89462e-05 | 2.094e-05 | 2(Loss) | true |
