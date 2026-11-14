
----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 688.492 | 0.156484 | 6391.15ms | 360584 | 640 | 3.90961e+08 | 499468 | 0.0481369 | 4.41416 | 1(Win) | true |
| simdjson (ondemand) | 298.958 | 0.254482 | 7254.68ms | 360584 | 160 | 1.37097e+09 | 1.15026e+06 | 0.0196733 | 10.166 | 2(Loss) | true |
