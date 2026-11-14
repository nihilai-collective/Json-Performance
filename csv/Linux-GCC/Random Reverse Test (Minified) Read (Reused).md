
----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 943.68 | 0.0625954 | 5912.6ms | 409725 | 320 | 2.14966e+07 | 414064 | 0.119332 | 5.39432 | 25.9311 | 5.17475 | 0.0113568 | 0.00648105 | 4.622e-06 | 1(Win) | true |
| simdjson (ondemand) | 522.397 | 0.0743081 | 5077.97ms | 409725 | 160 | 4.94283e+07 | 747983 | 0.0638894 | 9.78542 | 43.9211 | 8.78386 | 0.0313973 | 0.013734 | 2.06541e-05 | 2(Loss) | true |
