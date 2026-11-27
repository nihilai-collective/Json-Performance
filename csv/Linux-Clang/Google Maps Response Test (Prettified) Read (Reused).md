
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2647.95 | 0.0947194 | 1728.32ms | 25388 | 160 | 12001.5 | 9143.63 | 0.151084 | 1.94669 | 8.87002 | 1.52639 | 0.0026964 | 3.54498e-05 | 2.14176e-05 | 1(Win) | true |
| simdjson (ondemand) | 2265.5 | 0.0422046 | 1875.63ms | 25388 | 4890 | 99484.7 | 10687.2 | 0.26318 | 2.25834 | 9.57381 | 1.55904 | 0.00348837 | 2.1845e-05 | 1.25335e-05 | 2(Loss) | true |
