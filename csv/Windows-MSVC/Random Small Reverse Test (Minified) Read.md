
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 497.009 | 0.306967 | 952.611ms | 4926 | 2560 | 2.15518e+06 | 9452.15 | 0.118748 | 6.10109 | 1(Win) | true |
| simdjson (ondemand) | 318.498 | 0.22149 | 1487.02ms | 4926 | 1280 | 1.36613e+06 | 14749.8 | 0.0816352 | 9.5278 | 2(Loss) | true |
