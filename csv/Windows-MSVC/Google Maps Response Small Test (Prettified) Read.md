
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1920.59 | 0.285401 | 481.318ms | 9378 | 30 | 5298.85 | 4656.67 | 0.431344 | 1.27967 | 1(Win) | true |
| Jsonifier | 1888.82 | 0.161302 | 504.146ms | 9378 | 40 | 2333.33 | 4735 | 0.0352113 | 1.30367 | 2(Loss) | true |
| Glaze | 1325.44 | 0.259491 | 731.172ms | 9378 | 2560 | 784848 | 6747.62 | 0.029533 | 1.85946 | 3(Loss) | true |
| simdjson (ondemand) | 1020.08 | 0.175121 | 898.26ms | 9378 | 40 | 9429.49 | 8767.5 | 0.0856164 | 2.41846 | 4(Loss) | true |
