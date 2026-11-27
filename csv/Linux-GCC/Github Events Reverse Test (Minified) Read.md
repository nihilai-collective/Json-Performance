
----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 967.422 | 0.0415538 | 6026.23ms | 53331 | 1280 | 610884 | 52573.1 | 0.1305 | 5.27536 | 19.2573 | 3.79366 | 0.0169979 | 0.00010269 | 6.48368e-05 | 1(Win) | true |
| simdjson (ondemand) | 475.37 | 0.0844538 | 5882.51ms | 53331 | 640 | 5.22533e+06 | 106991 | 0.0471494 | 10.7351 | 36.9571 | 7.48217 | 0.0721766 | 0.000141774 | 9.4633e-05 | 2(Loss) | true |
