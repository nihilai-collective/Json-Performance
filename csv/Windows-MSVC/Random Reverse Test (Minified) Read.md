
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 527.173 | 0.340924 | 9589.63ms | 409725 | 30 | 1.91564e+08 | 741207 | 0.0931782 | 4.69595 | 1(Win) | true |
| simdjson (ondemand) | 257.58 | 0.301742 | 9751.78ms | 409725 | 160 | 3.35237e+09 | 1.51698e+06 | 2.19874 | 9.61169 | 2(Loss) | true |
