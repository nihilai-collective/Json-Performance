
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 609.708 | 0.192838 | 854.123ms | 4926 | 2560 | 565157 | 7705 | 0.353628 | 4.97184 | 1(Win) | true |
| simdjson (ondemand) | 362.501 | 0.15975 | 1385.09ms | 4926 | 4890 | 2.09586e+06 | 12959.4 | 0.226511 | 8.37008 | 2(Loss) | true |
