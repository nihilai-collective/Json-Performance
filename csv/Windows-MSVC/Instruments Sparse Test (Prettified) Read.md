
----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5874.98 | 0.168411 | 2989.87ms | 183677 | 640 | 1.61367e+06 | 29815.9 | 0.248826 | 0.516846 | 1(Win) | true |
| simdjson (ondemand) | 4834.97 | 0.132013 | 3620.08ms | 183677 | 640 | 1.46399e+06 | 36229.4 | 0.00172515 | 0.628169 | 2(Loss) | true |
