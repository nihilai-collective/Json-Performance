
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2397.63 | 1.84749 | 3966.91ms | 83958 | 640 | 2.43615e+08 | 33394.8 | 1.46925 | 1.26651 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2129.48 | 1.97235 | 4563.38ms | 83958 | 30 | 1.64993e+07 | 37600 | 0.0797236 | 1.42621 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2055.21 | 0.929129 | 4786.48ms | 83958 | 80 | 1.04822e+07 | 38958.8 | 0.393097 | 1.47776 | 2(Tie) | true |
| simdjson (ondemand) | 1357.41 | 0.65823 | 6468.43ms | 83958 | 4890 | 7.37168e+08 | 58986.3 | 0.859363 | 2.2375 | 4(Loss) | true |
