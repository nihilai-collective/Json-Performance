
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1551.11 | 0.316573 | 434.452ms | 6701 | 30 | 5103.45 | 4120 | 0.324675 | 1.95569 | 1(Win) | true |
| Jsonifier (two-stage) | 1338.81 | 0.374939 | 501.458ms | 6701 | 30 | 9609.2 | 4773.33 | 0.350385 | 2.25343 | 2(Loss) | true |
| Glaze | 1166.16 | 0.228219 | 569.204ms | 6701 | 40 | 6256.41 | 5480 | 0.243902 | 2.59838 | 3(Loss) | true |
| simdjson (ondemand) | 1013.3 | 0.283781 | 676.129ms | 6701 | 30 | 9609.2 | 6306.67 | 0.942408 | 2.992 | 4(Loss) | true |
