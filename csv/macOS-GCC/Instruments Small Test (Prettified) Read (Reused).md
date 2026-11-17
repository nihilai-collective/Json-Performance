
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2809.38 | 0.647858 | 282.086ms | 7932 | 1280 | 389506 | 2692.6 | 0.485147 | 1(Win) | true |
| Jsonifier (two-stage) | 2467.59 | 0.176568 | 326.827ms | 7932 | 4890 | 143269 | 3065.56 | 0.165357 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2015.49 | 0.456742 | 394.324ms | 7932 | 1280 | 376145 | 3753.2 | 0.771997 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1979.83 | 1.22003 | 408.712ms | 7932 | 80 | 173836 | 3820.8 | 0 | 3(Tie) | true |
| simdjson (ondemand) | 1722.62 | 0.413614 | 470.753ms | 7932 | 2560 | 844533 | 4391.3 | 0.206799 | 5(Loss) | true |
