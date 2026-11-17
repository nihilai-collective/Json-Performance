
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2296.55 | 0.0883229 | 3076.75ms | 56369 | 80 | 34195.1 | 23408 | 0.0525738 | 2.20482 | 9.42132 | 1.80171 | 0.00292426 | 2.83844e-05 | 2.28406e-05 | 1(Win) | true |
| Glaze | 2025.17 | 0.143447 | 3400.13ms | 56369 | 80 | 115993 | 26544.8 | 0.0821928 | 2.49877 | 11.2196 | 2.27577 | 0.00530744 | 0.000117973 | 0.000100011 | 2(Loss) | true |
| Jsonifier (two-stage) | 1826.71 | 0.0283136 | 3680.06ms | 56369 | 2560 | 177735 | 29428.7 | 0.0298294 | 2.77343 | 12.2726 | 2.12839 | 0.00487188 | 3.76218e-05 | 2.22377e-05 | 3(Loss) | true |
| simdjson (reflection) | 1572.25 | 0.036573 | 4186.75ms | 56369 | 1280 | 200158 | 34191.7 | 0.00190565 | 3.22498 | 13.7995 | 2.40389 | 0.00430861 | 7.15985e-05 | 5.22922e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1326.39 | 0.0221978 | 4790.9ms | 56369 | 4890 | 395794 | 40529.4 | 0.125338 | 3.80709 | 15.0257 | 2.78824 | 0.008408 | 3.83683e-05 | 2.33743e-05 | 5(Loss) | true |
