
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1643.32 | 0.0605195 | 3890.49ms | 65103 | 4890 | 2.55656e+06 | 37781.5 | 0.019148 | 1(Win) | true |
| Jsonifier | 1609.41 | 0.285699 | 3862.6ms | 65103 | 1280 | 1.55488e+07 | 38577.6 | 0.648989 | 2(Loss) | true |
| simdjson (reflection) | 1481.9 | 0.220254 | 4612.32ms | 65103 | 320 | 2.72496e+06 | 41896.8 | 0.30837 | 3(Loss) | true |
| Glaze | 1446.12 | 0.303132 | 4323.91ms | 65103 | 2560 | 4.33607e+07 | 42933.5 | 1.57382 | 4(Loss) | true |
| simdjson (ondemand) | 1223.73 | 0.325134 | 5126.35ms | 65103 | 80 | 2.17695e+06 | 50736 | 0.47081 | 5(Loss) | true |
