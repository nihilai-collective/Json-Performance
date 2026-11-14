
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 541.448 | 0.13769 | 9215.89ms | 409725 | 80 | 7.89894e+07 | 721665 | 0.0650848 | 5.61306 | 1(Win) | true |
| simdjson (ondemand) | 334.424 | 0.155407 | 7374.89ms | 409725 | 320 | 1.05508e+09 | 1.16841e+06 | 0.153837 | 9.08771 | 2(Loss) | true |
