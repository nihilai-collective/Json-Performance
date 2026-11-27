
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10312.8 | 0.0926056 | 745.725ms | 78778 | 40 | 1820.51 | 7285 | 0.0228728 | 0.239072 | 1(Win) | true |
| Glaze | 4813.75 | 0.153078 | 1637.1ms | 78778 | 2560 | 1.4612e+06 | 15607.1 | 0.0528385 | 0.513359 | 2(Loss) | true |
