
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 825.576 | 0.0396836 | 1271.41ms | 4630 | 4890 | 22028.2 | 5348.4 | 0.0672878 | 6.17178 | 27.4305 | 5.71922 | 0.00805253 | 6.93441e-05 | 2.10683e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 783.336 | 0.0702838 | 1297.57ms | 4630 | 1280 | 20090.3 | 5636.8 | 0.212973 | 6.50308 | 30.2782 | 6.19309 | 0.00882728 | 5.3152e-05 | 1.61987e-05 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 743.093 | 0.110231 | 1330.37ms | 4630 | 640 | 27457.7 | 5942.07 | 0.0354864 | 6.84346 | 31.5719 | 6.12419 | 0.00477322 | 0.000116766 | 5.36582e-05 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 742.865 | 0.136308 | 1333.07ms | 4630 | 640 | 42011.4 | 5943.89 | 0.0166427 | 6.85143 | 32.3581 | 5.67344 | 0.00254961 | 3.64471e-05 | 3.37473e-06 | 3(Tie) | true |
