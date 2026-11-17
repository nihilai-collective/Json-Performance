
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1381.89 | 0.0763032 | 4383.26ms | 53331 | 640 | 504750 | 36804.8 | 0.252386 | 2.19783 | 1(Win) | true |
| Glaze | 1330.68 | 0.0449885 | 4514.47ms | 53331 | 1280 | 378467 | 38221.5 | 0.296115 | 2.28253 | 2(Loss) | true |
| Jsonifier (two-stage) | 1222.22 | 0.0552148 | 4845.16ms | 53331 | 1280 | 675741 | 41613 | 0.289394 | 2.48463 | 3(Loss) | true |
| simdjson (ondemand) | 845.861 | 0.0688451 | 6577.89ms | 53331 | 4890 | 8.37947e+06 | 60128.6 | 0.0541594 | 3.59157 | 4(Loss) | true |
