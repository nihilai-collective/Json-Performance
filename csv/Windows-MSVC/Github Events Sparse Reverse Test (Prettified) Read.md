
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4867.66 | 0.10313 | 1287.37ms | 65103 | 640 | 110742 | 12755 | 0.0514769 | 0.623158 | 1(Win) | true |
| simdjson (ondemand) | 3639.87 | 0.271909 | 1750.62ms | 65103 | 80 | 172095 | 17057.5 | 0.204768 | 0.834115 | 2(Loss) | true |
