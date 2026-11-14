
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2419.97 | 0.0858162 | 833.302ms | 2821 | 2560 | 2330.06 | 1111.72 | 0.0423574 | 2.20039 | 8.56079 | 1.48671 | 0.000359469 | 6.38349e-05 | 1.26008e-05 | 1(Win) | true |
| simdjson (ondemand) | 2208.06 | 0.0575826 | 843.588ms | 2821 | 4890 | 2407 | 1218.41 | 0.0209088 | 2.40561 | 9.0646 | 1.44631 | 0.000363328 | 4.25526e-05 | 4.3495e-06 | 2(Loss) | true |
