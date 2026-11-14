
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2601.6 | 0.0261684 | 6616.18ms | 124597 | 2560 | 365702 | 45673.7 | 0.0730696 | 1.93027 | 9.32803 | 1.41992 | 0.00523687 | 1.14745e-05 | 8.11993e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.55 | 0.0808743 | 6861.47ms | 124597 | 640 | 996370 | 48787.7 | 0.0206197 | 2.05728 | 8.45642 | 1.55536 | 0.00546107 | 9.07927e-06 | 5.68081e-06 | 2(Loss) | true |
| Jsonifier | 2384.97 | 0.079646 | 6976.97ms | 124597 | 160 | 251940 | 49822.4 | 0.0410375 | 2.11882 | 9.41571 | 1.67292 | 0.00798575 | 2.6686e-05 | 1.94126e-05 | 3(Loss) | true |
| simdjson (reflection) | 2309.85 | 0.185734 | 7175.94ms | 124597 | 80 | 730334 | 51442.8 | 0.0287295 | 2.17486 | 8.77216 | 1.46003 | 0.00334599 | 8.72814e-06 | 3.71197e-06 | 4(Loss) | true |
| Glaze | 2135.68 | 0.0865016 | 7617ms | 124597 | 320 | 741213 | 55638.1 | 0.0218985 | 2.3556 | 10.9291 | 2.09469 | 0.0104897 | 5.41747e-06 | 2.15695e-06 | 5(Loss) | true |
