
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1759.34 | 0.0765506 | 3633.86ms | 53331 | 4890 | 2.39479e+06 | 28908.8 | 0.164998 | 2.88019 | 8.59966 | 1.71939 | 0.0120526 | 0.000222015 | 0.000109502 | 1(Win) | true |
| Jsonifier (two-stage) | 1455.88 | 0.143654 | 4266.34ms | 53331 | 1280 | 3.2237e+06 | 34934.4 | 0.453821 | 3.4873 | 11.455 | 1.97896 | 0.0162215 | 0.000198847 | 8.66054e-05 | 2(Loss) | true |
| Glaze | 1444.98 | 0.0783503 | 4269.8ms | 53331 | 2560 | 1.94695e+06 | 35197.9 | 0.23629 | 3.53384 | 11.7063 | 2.2495 | 0.0220948 | 0.000111633 | 5.12937e-05 | 3(Loss) | true |
| simdjson (ondemand) | 961.068 | 0.105491 | 6046.21ms | 53331 | 1280 | 3.98927e+06 | 52920.7 | 0.3795 | 5.28567 | 15.5852 | 2.7722 | 0.0154296 | 0.000133468 | 5.37475e-05 | 4(Loss) | true |
