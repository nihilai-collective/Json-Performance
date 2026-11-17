
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11261.4 | 0.0742711 | 714.976ms | 83958 | 1280 | 35693.5 | 7110 | 0.032975 | 0.268439 | 1(Win) | true |
| simdjson (stage-1) | 11108.1 | 0.0324795 | 730.385ms | 83958 | 160 | 876.965 | 7208.12 | 0.0606586 | 0.272078 | 2(Loss) | true |
