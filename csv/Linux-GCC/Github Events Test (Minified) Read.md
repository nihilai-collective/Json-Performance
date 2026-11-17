
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22656 | 0.0249942 | 231.846ms | 53331 | 160 | 50.3723 | 2244.89 | 0.0553728 | 0.107916 | 1(Win) | true |
| simdjson (stage-1) | 16380.2 | 0.25687 | 314.91ms | 53331 | 1280 | 81425.5 | 3105 | 0.0283394 | 0.149811 | 2(Loss) | true |
