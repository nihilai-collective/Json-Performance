
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2462.22 | 0.118532 | 3403.16ms | 53331 | 2560 | 1.53467e+06 | 20656.4 | 0.0557459 | 2.06086 | 6.33003 | 1.20325 | 0.0086022 | 5.39159e-05 | 2.54015e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1920.5 | 0.0801167 | 4013.35ms | 53331 | 4890 | 2.20132e+06 | 26482.8 | 0.123242 | 2.65105 | 9.18824 | 1.46346 | 0.0123849 | 5.18888e-05 | 1.80108e-05 | 2(Loss) | true |
| Glaze | 1905.45 | 0.123793 | 4014.29ms | 53331 | 1280 | 1.39754e+06 | 26692.1 | 0.156154 | 2.67842 | 9.43009 | 1.73225 | 0.0179317 | 3.89812e-05 | 1.82674e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1139.05 | 0.114246 | 5764.58ms | 53331 | 1280 | 3.33093e+06 | 44651.5 | 0.0401463 | 4.46325 | 13.5687 | 2.31259 | 0.0110572 | 3.57877e-05 | 1.65242e-05 | 4(Loss) | true |
