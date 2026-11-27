
----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 476.898 | 0.304917 | 942.254ms | 4669 | 1280 | 1.03746e+06 | 9336.8 | 0.0643032 | 1(Win) | true |
| simdjson (ondemand) | 197.484 | 0.16549 | 2339.96ms | 4669 | 2560 | 3.56424e+06 | 22547.2 | 1.37609 | 2(Loss) | true |
