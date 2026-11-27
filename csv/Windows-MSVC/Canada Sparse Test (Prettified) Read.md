
----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11193.6 | 0.159009 | 5627.47ms | 5212421 | 160 | 7.97816e+07 | 444089 | 0.10778 | 0.271481 | 1(Win) | true |
| simdjson (ondemand) | 8465.1 | 0.0708319 | 7466.18ms | 5212421 | 640 | 1.10727e+08 | 587229 | 0.0869592 | 0.358978 | 2(Loss) | true |
