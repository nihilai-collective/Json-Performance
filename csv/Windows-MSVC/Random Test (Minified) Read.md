
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22612.1 | 0.0398313 | 1992.67ms | 461466 | 40 | 2403.85 | 19462.5 | 0.106929 | 0.109373 | 1(Win) | true |
| simdjson (stage-1) | 18621.7 | 0.192987 | 2400.8ms | 461466 | 1280 | 2.66261e+06 | 23633.1 | 0.365596 | 0.132787 | 2(Loss) | true |
