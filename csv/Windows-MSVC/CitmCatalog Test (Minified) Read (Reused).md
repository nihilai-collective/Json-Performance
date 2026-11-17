
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1787.59 | 0.148685 | 7738.81ms | 500299 | 160 | 2.51987e+07 | 266908 | 0.00749379 | 1.70011 | 1(Win) | true |
| Jsonifier (two-stage) | 1439.8 | 0.0900824 | 9422.89ms | 500299 | 320 | 2.85156e+07 | 331380 | 0.0298085 | 2.11073 | 2(Loss) | true |
| Glaze | 926.524 | 0.106432 | 7032.57ms | 500299 | 160 | 4.80627e+07 | 514959 | 0.0651326 | 3.28033 | 3(Loss) | true |
| simdjson (ondemand) | 606.8 | 0.12444 | 5195.76ms | 500299 | 320 | 3.06363e+08 | 786293 | 0.182288 | 5.00872 | 4(Loss) | true |
