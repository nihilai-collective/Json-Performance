
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1507.02 | 0.0380869 | 60.0463ms | 905 | 320 | 15.2251 | 572.703 | 0.101049 | 1.57041 | 1(Win) | true |
| Glaze | 1434.54 | 0.0501997 | 82.399ms | 905 | 80 | 7.29731 | 601.638 | 0.0477634 | 1.65001 | 2(Loss) | true |
| Jsonifier | 1367.9 | 0.179541 | 61.6606ms | 905 | 40 | 51.3308 | 630.95 | 0.044926 | 1.73227 | 3(Loss) | true |
| simdjson (ondemand) | 383.563 | 0.0481484 | 233.053ms | 905 | 40 | 46.9513 | 2250.15 | 1.03866 | 6.3821 | 4(Loss) | true |
