
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22175.7 | 0.272033 | 2066.99ms | 461466 | 320 | 932650 | 19845.6 | 0.380082 | 0.111492 | 1(Win) | true |
| simdjson (stage-1) | 15656.9 | 0.199349 | 2841ms | 461466 | 640 | 2.00945e+06 | 28108.3 | 0.0669736 | 0.157972 | 2(Loss) | true |
