
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1029.63 | 0.782932 | 5001.71ms | 53331 | 640 | 9.57249e+07 | 49396.7 | 0.0192916 | 2.40114 | 1(Win) | true |
| Glaze | 963.817 | 0.235659 | 5389.89ms | 53331 | 2560 | 3.95893e+07 | 52769.8 | 0.0932095 | 2.56708 | 2(Loss) | true |
| Jsonifier (two-stage) | 946.678 | 0.214277 | 5490.56ms | 53331 | 1280 | 1.69635e+07 | 53725.2 | 0.480719 | 2.61365 | 3(Loss) | true |
| simdjson (ondemand) | 657.695 | 0.283666 | 7821.72ms | 53331 | 320 | 1.53984e+07 | 77331.2 | 0.00242458 | 3.76231 | 4(Loss) | true |
