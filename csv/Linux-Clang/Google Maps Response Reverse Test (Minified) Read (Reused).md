
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.775 | 0.0556041 | 2165.09ms | 11812 | 1280 | 74364.2 | 13707.9 | 0.087943 | 6.21246 | 28.2974 | 5.72054 | 0.0147462 | 6.0783e-05 | 3.51205e-05 | 1(Win) | true |
| simdjson (ondemand) | 730.044 | 0.176808 | 2360.87ms | 11812 | 80 | 59544.7 | 15430.3 | 0.00113412 | 7.07149 | 32.0207 | 5.86031 | 0.0130799 | 2.85726e-05 | 9.52421e-06 | 2(Loss) | true |
