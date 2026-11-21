
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1146.46 | 0.357099 | 5524.01ms | 65103 | 1280 | 4.78705e+07 | 54155.2 | 0.361523 | 2.15812 | 1(Win) | true |
| Glaze | 1115.2 | 0.222084 | 5573.93ms | 65103 | 2560 | 3.91357e+07 | 55673.7 | 0.0574266 | 2.21872 | 2(Loss) | true |
| Jsonifier | 1049.48 | 0.864057 | 6050.4ms | 65103 | 30 | 7.83903e+06 | 59160 | 0.893455 | 2.35757 | 3(Loss) | true |
| simdjson (ondemand) | 813.054 | 0.346451 | 7673.96ms | 65103 | 640 | 4.47949e+07 | 76362.8 | 0.0114571 | 3.0438 | 4(Loss) | true |
