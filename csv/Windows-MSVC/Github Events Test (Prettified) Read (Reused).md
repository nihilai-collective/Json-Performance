
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.79 | 0.259093 | 5239.42ms | 65103 | 40 | 533583 | 44577.5 | 0.0653863 | 2.18125 | 1(Win) | true |
| simdjson (ondemand) | 1126.11 | 0.122371 | 6240.09ms | 65103 | 2560 | 1.16531e+07 | 55134.1 | 0.0542417 | 2.69777 | 2(Loss) | true |
