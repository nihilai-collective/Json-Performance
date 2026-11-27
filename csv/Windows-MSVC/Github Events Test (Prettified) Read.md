
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1170.96 | 0.484393 | 5400.77ms | 65103 | 160 | 1.05545e+07 | 53022.5 | 0.4903 | 2.11293 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.21 | 0.157888 | 5669.8ms | 65103 | 4890 | 3.79872e+07 | 55823.2 | 0.383612 | 2.22469 | 2(Loss) | true |
| Glaze | 1106.66 | 0.172352 | 5786.65ms | 65103 | 4890 | 4.57207e+07 | 56103.1 | 0.131311 | 2.23578 | 3(Loss) | true |
| simdjson (ondemand) | 737.941 | 0.194681 | 8327.78ms | 65103 | 2560 | 6.86821e+07 | 84135.5 | 0.290973 | 3.35373 | 4(Loss) | true |
