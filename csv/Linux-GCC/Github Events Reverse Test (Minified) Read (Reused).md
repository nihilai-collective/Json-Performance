
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1140.82 | 0.0942969 | 5777.08ms | 53331 | 320 | 565546 | 44582.2 | 0.0192869 | 4.47231 | 16.9978 | 3.2803 | 0.0140765 | 2.20322e-05 | 1.2774e-05 | 1(Win) | true |
| simdjson (ondemand) | 518.934 | 0.0627009 | 5721.65ms | 53331 | 1280 | 4.83384e+06 | 98009.3 | 0.0100032 | 9.78986 | 34.7504 | 6.98331 | 0.064878 | 0.000103217 | 7.47103e-05 | 2(Loss) | true |
