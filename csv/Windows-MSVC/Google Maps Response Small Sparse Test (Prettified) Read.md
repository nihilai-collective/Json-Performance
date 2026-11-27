
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2845.25 | 0.292742 | 360.621ms | 9378 | 30 | 2540.23 | 3143.33 | 0.632244 | 1.05914 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2402.57 | 0.203761 | 392.194ms | 9378 | 40 | 2301.28 | 3722.5 | 3.11634 | 1.2589 | -(Loss) | false |
