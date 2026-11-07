
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1062.8 | 0.588709 | 4787.54ms | 53331 | 80 | 6.34959e+06 | 47855 | 0.00522439 | 2.32799 | 1(Win) | true |
| Glaze | 1049.24 | 0.188647 | 4950.05ms | 53331 | 2560 | 2.14066e+07 | 48473.6 | 0.26258 | 2.35812 | 2(Loss) | true |
| Jsonifier (two-stage) | 1023.53 | 0.182631 | 5018.73ms | 53331 | 4890 | 4.02731e+07 | 49691 | 0.00780549 | 2.417 | 3(Loss) | true |
| simdjson (ondemand) | 650.218 | 0.139315 | 7860.14ms | 53331 | 4890 | 5.80692e+07 | 78220.6 | 0.361822 | 3.80623 | 4(Loss) | true |
