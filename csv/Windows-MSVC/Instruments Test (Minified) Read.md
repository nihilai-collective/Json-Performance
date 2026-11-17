
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9976.38 | 0.0343009 | 1039.23ms | 108313 | 4890 | 61678.7 | 10354 | 0.193509 | 0.303528 | 1(Win) | true |
| simdjson (stage-1) | 9186.88 | 0.0613422 | 1125.03ms | 108313 | 2560 | 121782 | 11243.8 | 0.0844929 | 0.329665 | 2(Loss) | true |
