
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 20601.8 | 0.0597697 | 2331.39ms | 500299 | 4890 | 936956 | 23159.2 | 0.241802 | 0.120031 | 1(Win) | true |
| simdjson (stage-1) | 16582.6 | 0.0679674 | 2880.38ms | 500299 | 4890 | 1.87009e+06 | 28772.4 | 0.10016 | 0.149151 | 2(Loss) | true |
